CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 520;
	title = 52002;

	CNtlTSGroup
	{
		gid = 0;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 52007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4111301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 5;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 52009;
				ctype = 1;
				idx = 4111301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 52008;
				gtype = 2;
				area = 52001;
				goal = 52004;
				grade = 132203;
				rwd = 100;
				sort = 52005;
				stype = 1;
				taid = 1;
				title = 52002;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSUseMail
			{
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 52014;
			nextlnk = 254;
			rwdtbl = 52001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4111301;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 52008;
			gtype = 2;
			oklnk = 2;
			area = 52001;
			goal = 52004;
			sort = 52005;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 52002;
		}
	}
}

