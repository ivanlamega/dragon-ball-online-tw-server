CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 220;
	title = 22002;

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
				conv = 22009;
				ctype = 1;
				idx = 4751301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 22008;
				gtype = 1;
				area = 22001;
				goal = 22004;
				grade = 132203;
				rwd = 100;
				sort = 22005;
				stype = 1;
				taid = 1;
				title = 22002;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 22008;
			gtype = 1;
			oklnk = 2;
			area = 22001;
			goal = 22004;
			sort = 22005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 22002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 22014;
			nextlnk = 254;
			rwdtbl = 22001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511601;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 22007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4751301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 13;
				minlvl = 5;
			}
			CDboTSCheckClrQst
			{
				or = "219;";
			}
		}
	}
}

