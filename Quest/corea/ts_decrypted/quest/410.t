CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 410;
	title = 41002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 41008;
				gtype = 0;
				area = 41001;
				goal = 41004;
				grade = 132203;
				rwd = 100;
				sort = 41005;
				stype = 1;
				taid = 1;
				title = 41002;
			}
			CDboTSActNPCConv
			{
				conv = 41009;
				ctype = 1;
				idx = 8512105;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 41014;
			nextlnk = 254;
			rwdtbl = 41001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8511104;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 41007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8512105;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 11;
				minlvl = 3;
			}
			CDboTSCheckClrQst
			{
				and = "409;";
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
			cont = 41008;
			gtype = 0;
			oklnk = 2;
			area = 41001;
			goal = 41004;
			sort = 41005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 41002;
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

