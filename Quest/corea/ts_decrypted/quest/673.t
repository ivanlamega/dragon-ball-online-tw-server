CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 673;
	title = 67302;

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
				conv = 67309;
				ctype = 1;
				idx = 4371402;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 67308;
				gtype = 1;
				area = 67301;
				goal = 67304;
				grade = 132203;
				rwd = 100;
				sort = 67305;
				stype = 2;
				taid = 1;
				title = 67302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 67307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4371402;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckClrQst
			{
				and = "672;";
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
			cont = 67308;
			gtype = 1;
			oklnk = 2;
			area = 67301;
			goal = 67304;
			sort = 67305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 67302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 67314;
			nextlnk = 254;
			rwdtbl = 67301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312109;
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

