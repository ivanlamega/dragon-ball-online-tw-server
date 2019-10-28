CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 450;
	title = 45002;

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
				cont = 45008;
				gtype = 0;
				area = 45001;
				goal = 45004;
				grade = 132203;
				rwd = 100;
				sort = 45005;
				stype = 2;
				taid = 1;
				title = 45002;
			}
			CDboTSActNPCConv
			{
				conv = 45009;
				ctype = 1;
				idx = 4511304;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 45007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4511304;
			}
			CDboTSCheckLvl
			{
				maxlvl = 17;
				minlvl = 9;
			}
			CDboTSCheckClrQst
			{
				and = "448;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 45008;
			gtype = 0;
			oklnk = 2;
			area = 45001;
			goal = 45004;
			sort = 45005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 45002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 45014;
			nextlnk = 254;
			rwdtbl = 45001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4151201;
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
	}
}

