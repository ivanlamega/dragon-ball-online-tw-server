CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 74;
	title = 7402;

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
				conv = 7409;
				ctype = 1;
				idx = 8751101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 7408;
				gtype = 1;
				area = 7401;
				goal = 7404;
				grade = 132203;
				rwd = 100;
				sort = 7405;
				stype = 2;
				taid = 1;
				title = 7402;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 7414;
			nextlnk = 254;
			rwdtbl = 7401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4072102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 7407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 8751101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 12;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 7408;
			gtype = 1;
			oklnk = 2;
			area = 7401;
			goal = 7404;
			sort = 7405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 7402;
		}
	}
}

