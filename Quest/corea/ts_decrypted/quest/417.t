CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 417;
	title = 41702;

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
				conv = 41709;
				ctype = 1;
				idx = 7711101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 41708;
				gtype = 0;
				area = 41701;
				goal = 41704;
				grade = 132203;
				rwd = 100;
				sort = 41705;
				stype = 1;
				taid = 1;
				title = 41702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 41707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 64;
			}
			CDboTSClickNPC
			{
				npcidx = 7711101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 12;
				minlvl = 4;
			}
			CDboTSCheckClrQst
			{
				and = "404;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 41708;
			gtype = 0;
			oklnk = 2;
			area = 41701;
			goal = 41704;
			sort = 41705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 41702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 41714;
			nextlnk = 254;
			rwdtbl = 41701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4371301;
			}
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

