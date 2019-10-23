CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 144;
	title = 14402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 14409;
				ctype = 1;
				idx = 3031204;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 14408;
				gtype = 1;
				area = 14401;
				goal = 14404;
				grade = 132203;
				rwd = 100;
				sort = 14405;
				stype = 2;
				taid = 1;
				title = 14402;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 14414;
			nextlnk = 254;
			rwdtbl = 14401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5062103;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 14408;
			gtype = 1;
			oklnk = 2;
			area = 14401;
			goal = 14404;
			sort = 14405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 14402;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 14407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031204;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckPCCls
			{
				clsflg = 3;
			}
			CDboTSCheckLvl
			{
				maxlvl = 26;
				minlvl = 18;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

