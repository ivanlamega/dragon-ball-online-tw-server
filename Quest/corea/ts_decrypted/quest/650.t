CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 650;
	title = 65002;

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
				conv = 65009;
				ctype = 1;
				idx = 1351208;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 65008;
				gtype = 1;
				area = 65001;
				goal = 65004;
				grade = 132203;
				rwd = 100;
				sort = 65005;
				stype = 2;
				taid = 1;
				title = 65002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 65007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1351208;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckClrQst
			{
				and = "649;";
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
			cont = 65008;
			gtype = 1;
			oklnk = 2;
			area = 65001;
			goal = 65004;
			sort = 65005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 65002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 65014;
			nextlnk = 254;
			rwdtbl = 65001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3182102;
			}
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

